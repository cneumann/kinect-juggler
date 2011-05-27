
#include "VRJOgreDummyApp.hpp"

// system header

#include <OGRE/OgreEntity.h>
#include <OGRE/OgreResourceGroupManager.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreSceneNode.h>


/* explicit */
VRJOgreDummyApp::VRJOgreDummyApp(vrj::Kernel* kernel)
    : VRJOgreApp(kernel)
{
}

/* virtual */
VRJOgreDummyApp::~VRJOgreDummyApp(void)
{
}

/* virtual */ void
VRJOgreDummyApp::contextInit(void)
{
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
