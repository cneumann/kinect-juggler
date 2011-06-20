
#include "VRJOgreDummyApp.hpp"

// system header

#include <jccl/Config/ConfigElement.h>

#include <OGRE/OgreEntity.h>
#include <OGRE/OgreResourceGroupManager.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreSceneNode.h>

// project header

#include <SkeletonMapper.hpp>

#define ENABLE_TRACE
#include <Trace.hpp>

/* explicit */
VRJOgreDummyApp::VRJOgreDummyApp(vrj::Kernel* kernel)
    : VRJOgreApp(kernel)
{
    TRACE_FUNC;
}

/* virtual */
VRJOgreDummyApp::~VRJOgreDummyApp(void)
{
    TRACE_FUNC;
}

/* virtual */ void
VRJOgreDummyApp::contextInit(void)
{
    TRACE_FUNC;

    VRJOgreApp::contextInit();

    Ogre::ResourceGroupManager* rgm = Ogre::ResourceGroupManager::getSingletonPtr();
    rgm->addResourceLocation("../data", "FileSystem");

    Ogre::Entity*    entity = sm_->createEntity("Head", "ogrehead.mesh");
    Ogre::SceneNode* node   = sm_->getRootSceneNode()->createChildSceneNode();

    node->attachObject(entity);
}

/* virtual */ void
VRJOgreDummyApp::draw(void)
{
    VRJOgreApp::draw();
}


/* virtual */ bool
VRJOgreDummyApp::configCanHandle(jccl::ConfigElementPtr element)
{
    TRACE_FUNC_MSG(element->getID());

    return VRJOgreApp::configCanHandle(element) ||
           SkeletonMapper::classConfigCanHandle(element);
}

/* virtual */ bool
VRJOgreDummyApp::configAdd(jccl::ConfigElementPtr element)
{
    TRACE_FUNC_MSG(element->getID());

    bool result(false);

    if(VRJOgreApp::configCanHandle(element) == true)
    {
        result = VRJOgreApp::configAdd(element);
    }

    return result;
}

/* virtual */ bool
VRJOgreDummyApp::configRemove(jccl::ConfigElementPtr element)
{
    TRACE_FUNC_MSG(element->getID());

    bool result(false);

    if(VRJOgreApp::configCanHandle(element) == true)
    {
        result = VRJOgreApp::configRemove(element);
    }

    return result;
}
