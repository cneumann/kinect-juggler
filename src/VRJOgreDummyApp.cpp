
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
    : VRJOgreApp(kernel),
      sklMap_  (NULL)
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
    rgm->addResourceLocation("../data/Sinbad.zip", "Zip");
    rgm->initialiseAllResourceGroups();

    Ogre::Entity*    entity = sm_->createEntity("Sinbad", "Sinbad.mesh");
    Ogre::SceneNode* node   = sm_->getRootSceneNode()->createChildSceneNode();

    node->attachObject(entity);
    
    if( sklMap_ != NULL)
    {
      sklMap_->setSkeleton(entity->getSkeleton());
    }
}

/* virtual */ void
VRJOgreDummyApp::preFrame(void)
{
}

/* virtual */ void
VRJOgreDummyApp::draw(void)
{
    VRJOgreApp::draw();
}

/*virtual */ void
VRJOgreDummyApp::postFrame(void)
{
  if(sklMap_ != NULL)
  {
    sklMap_->apply();
    Ogre::Entity* entity = sm_->getEntity("Head");
    Ogre::Skeleton* skel = entity->getSkeleton();
    Ogre::Skeleton::BoneIterator bIt = skel->getBoneIterator();

    for(bIt.begin(); bIt.hasMoreElements(); bIt.moveNext())
    { 
      std::string      name;
      Ogre::Quaternion orientation;
      Ogre::Vector3    position;
      name        = (*bIt.current())->getName();
      orientation = (*bIt.current())->getOrientation();
      position    = (*bIt.current())->getPosition();
#if 1 
      if ( name == "Root" )
      {
        printf("bone2.......[%s]\nposition2...[%f,%f,%f]\norientation2[%f,%f,%f,%f]\n",
                    name.c_str(),
                    position.x,
                    position.y,
                    position.z,
                    orientation.w,
                    orientation.x,
                    orientation.y,
                    orientation.z);
      }
#endif
            
    }
  }
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
VRJOgreDummyApp::configCanHandle(jccl::ConfigElementPtr element)
{
    TRACE_FUNC_MSG(element->getID());

    return VRJOgreApp::configCanHandle(element) ||
           SkeletonMapper::classConfigCanHandle(element);
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
