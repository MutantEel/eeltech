//
//  OALSoundSystem.hpp
//  EelTechTest
//
//  Created by Sean on 8/1/13.
//  Copyright (c) 2013 Mutant Eel. All rights reserved.
//

#include <Artemis/EntityProcessingSystem.hpp>
#include <Artemis/ComponentMapper.hpp>
#include <Artemis/Entity.hpp>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#ifndef EelTechTest_OALSoundSystem_hpp
#define EelTechTest_OALSoundSystem_hpp

namespace eeltech
{

class SoundComponent : artemis::Component
{
	public:
	
		enum State
		{
			PlayRequested,
			PauseRequested,
			StopRequested,
			Playing,
			Paused,
			Stopped,
		};
	
		SoundComponent();
		
		void setPitch(float pitch);
		void setGain(float gain);
		void setLooping(bool shouldLoop);
		void setFileName(std::string fileName);
	
		std::string fileName;
		float gain;
		float pitch;
		bool shouldLoop;
		
		State state;
		unsigned int bufferId;
		unsigned int sourceId;
		
		bool gainModified;
		bool pitchModified;
		bool loopModified;
		bool fileNameModified;
	
	// MARK: FIXME_FEATURE add listener functionality
};
	
	
class OALSoundSystem : public artemis::EntityProcessingSystem
{
public:
	OALSoundSystem();
	virtual ~OALSoundSystem();
	
	virtual void initialize();
	
protected:
	artemis::ComponentMapper<SoundComponent> soundMapper;
	
	virtual void processEntity(artemis::Entity& e);
	virtual void added(artemis::Entity& e);
	virtual void removed(artemis::Entity& e);
	
	
	//sound buffers functionality
	unsigned int createBuffer();
	void releaseBuffer(unsigned int bufferId);
	bool setBufferData(unsigned int bufferId, int format, char* data, int dataSize, int frequency);
	unsigned int getBufferForFile(std::string filename);
	
	
	ALCdevice* device;
	ALCcontext* context;
	std::map<std::string, unsigned int> soundBuffers;
};


}


#endif
