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

	
class OALSoundSystem : public artemis::EntityProcessingSystem
{
public:
	OALSoundSystem();
	virtual ~OALSoundSystem();
	
	virtual void initialize();
	
protected:
	
	virtual void processEntity(artemis::Entity& e);
	virtual void added(artemis::Entity& e);
	
	ALCdevice* device;
	ALCcontext* context;
};


}


#endif
