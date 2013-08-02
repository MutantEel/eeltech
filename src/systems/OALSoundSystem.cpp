//
//  OALSoundSystem.cpp
//  EelTech
//
//  Created by Sean on 8/1/13.
//  Copyright (c) 2013 Mutant Eel. All rights reserved.
//

#include <EelTech/systems/OALSoundSystem.hpp>


namespace eeltech
{

	
SoundComponent::SoundComponent() : gain(1.0), pitch(1.0), shouldLoop(false), state(SoundComponent::Stopped), bufferId(0), sourceId(0), gainModified(false), pitchModified(false), loopModified(false), fileNameModified(false), fileName("")
{			
}
		

void SoundComponent::setPitch(float pitch)
{
	this->pitch = pitch;
	pitchModified = true;
}


void SoundComponent::setGain(float gain)
{
	this->gain = gain;
	gainModified = true;
}


void SoundComponent::setLooping(bool shouldLoop)
{
	this->shouldLoop = shouldLoop;
	loopModified = true;
}


void SoundComponent::setFileName(std::string fileName)
{
	this->fileName = fileName;
	fileNameModified = true;
}

	
	
	
	
	
	
OALSoundSystem::OALSoundSystem() : device(NULL), context(NULL)
{
	
}


OALSoundSystem::~OALSoundSystem()
{
	if(context)
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		context = NULL;
	}
	
	if(device)
	{
		alcCloseDevice(device);
		device = NULL;
	}
}


void OALSoundSystem::initialize()
{
	device = alcOpenDevice(NULL);
	
	if (!device)
	{
#ifdef DEBUG
		std::cout << "Could not open default OpenAL device." << std::endl;
#endif
		return;
	}
	
	context = alcCreateContext(device, NULL);
	
	if (!context)
	{
#ifdef DEBUG
		std::cout << "Failed to create OpenAL context for default device." << std::endl;
#endif
		return;
	}
	
	if (!alcMakeContextCurrent(context))
	{
#ifdef DEBUG
		std::cout << "Failed to set current OpenAL context." << std::endl;
#endif
		return;
	}
	
	if(alGetError() != 0)
	{
#ifdef DEBUG
		std::cout << "Error initializing audio" << std::endl;
#endif
		return;
	}

}
	
	
void OALSoundSystem::processEntity(artemis::Entity& e)
{
	SoundComponent* comp = soundMapper.get(e);
	
	if(comp)
	{
		if(comp->fileNameModified)
		{
			comp->bufferId = getBufferForFile(comp->fileName);
			
			if(comp->bufferId != 0)
			{
				alSourcei(comp->sourceId, AL_BUFFER, comp->bufferId);
			}

			comp->fileNameModified = false;
		}
		
		if(comp->gainModified)
		{
			alSourcef(comp->sourceId, AL_GAIN, comp->gain);
			comp->gainModified = false;
		}
		
		if(comp->pitchModified)
		{
			alSourcef(comp->sourceId, AL_PITCH, comp->pitch);
			comp->pitchModified = false;
		}
		
		if(comp->loopModified)
		{
			alSourcef(comp->sourceId, AL_LOOPING, comp->shouldLoop);
			comp->loopModified = false;
		}
		
		// MARK: FIXME_FEATURE check transformation component for position
		//alSourcefv(oalId, AL_POSITION, (ALfloat*)&position);
		
		// MARK: FIXME_FEATURE check physics component for velocity
		// alSourcefv(oalId, AL_VELOCITY, (ALfloat*)&velocity);
		
		switch(comp->state)
		{
			case SoundComponent::StopRequested:
				alSourceStop(comp->sourceId);
				comp->state = SoundComponent::Stopped;
				break;
			case SoundComponent::PlayRequested:
				alSourcePlay(comp->sourceId);
				comp->state = SoundComponent::Playing;
				break;
			case SoundComponent::PauseRequested:
				alSourcePause(comp->sourceId);
				comp->state = SoundComponent::Paused;
				break;
			case SoundComponent::Playing:
				{
					ALenum state;
					alGetSourcei(comp->sourceId, AL_SOURCE_STATE, &state);
				
					if(state == AL_STOPPED)
					{
						comp->state = SoundComponent::Stopped;
					}
				}
				break;
				default:
				break;
		}
	}
}
	
	
void OALSoundSystem::added(artemis::Entity& e)
{
	SoundComponent* comp = soundMapper.get(e);
	
	if(comp)
	{
		alGenSources(1, &comp->sourceId);
	}
}
	

void OALSoundSystem::removed(artemis::Entity& e)
{
	SoundComponent* comp = soundMapper.get(e);
		
	if(comp)
	{
		alDeleteSources(1, &comp->sourceId);
	}
}
	 
	
unsigned int OALSoundSystem::createBuffer()
{
	unsigned int bufferId = 0;
	alGenBuffers(1, &bufferId);
	
	if((alGetError() != AL_NO_ERROR) || (AL_NONE == bufferId))
	{
#ifdef DEBUG
		std::cout << "Failed to generate sound buffer" << std::endl;
#endif
		return 0;
	}
	
	return bufferId;
}


void OALSoundSystem::releaseBuffer(unsigned int bufferId)
{
	alDeleteBuffers(1, &bufferId);
}


bool OALSoundSystem::setBufferData(unsigned int bufferId, int format, char* data, int dataSize, int frequency)
{
	alBufferData(bufferId, format, data, dataSize, frequency);
	return alGetError() == AL_NO_ERROR;
}

	
unsigned int OALSoundSystem::getBufferForFile(std::string filename)
{
	// MARK: FIXME_FEATURE need to implement loading of sound files
	
	return 0;
}


}
