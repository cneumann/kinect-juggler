
#include "SkeletonMapper.hpp"
#include "OgreUtils.hpp"

// system header

#include <jccl/Config/ConfigElement.h>

#include <OGRE/OgreBone.h>

// project header

#define ENABLE_TRACE
#include <Trace.hpp>


/* explicit */
SkeletonMapper::SkeletonMapper()
    : jccl::ConfigElementHandler(),
      skel_                     (),
      positions_                (),
      boneProxyNames_           ()
{
    TRACE_FUNC;
}

void
SkeletonMapper::setSkeleton(Ogre::Skeleton* skel)
{
    skel_ = Ogre::SkeletonPtr(skel);
    printf("objectName[%s]\n",skel_->getName().c_str());
    Ogre::Skeleton::BoneIterator bIt = skel_->getBoneIterator();

    for(bIt.begin(); bIt.hasMoreElements(); bIt.moveNext())
    {
            (*bIt.current())->setManuallyControlled(true);
            (*bIt.current())->setInheritOrientation(false);
            //bIt.current()->resetOrientation();
            //(*bIt.current())->setInitialState();
    }
    
    initJointMap();
}

Ogre::Skeleton*
SkeletonMapper::getSkeleton(void)
{
  return skel_.get();
}

void
SkeletonMapper::apply(void)
{
    if(skel_.get() == NULL)
        return;

    Ogre::Skeleton::BoneIterator bIt = skel_->getRootBoneIterator();

    for(; bIt.hasMoreElements(); bIt.moveNext())
    {
        applyBone(bIt.peekNext());
    }
}

/* static */ bool
SkeletonMapper::classConfigCanHandle(jccl::ConfigElementPtr element)
{
    TRACE_FUNC;

    return element->getID() == "skeleton";
}

/* virtual */ bool
SkeletonMapper::configCanHandle(jccl::ConfigElementPtr element)
{
    TRACE_FUNC;

    return classConfigCanHandle(element);
}

/* virtual */ bool
SkeletonMapper::configAdd(jccl::ConfigElementPtr element)
{
    TRACE_FUNC;

    // should map OpenNI joint -> OGRE bone handle, store in jointMap_
    std::string ogreKey("ogre_name");
    std::string proxyKey("proxy");
    std::vector<jccl::ConfigElementPtr> childElements = 
                                             element->getChildElements();
    
    for ( std::vector<jccl::ConfigElementPtr>::iterator elmIt = 
                                             childElements.begin(); 
          elmIt != childElements.end(); 
          ++elmIt ) 
    {
      for ( int i = 0; i < (*elmIt)->getNum(ogreKey); ++i )
      {
        boneProxyNames_.insert(BoneProxyNameMap::value_type(
                          (*elmIt)->getProperty<std::string>(ogreKey, i),
                          (*elmIt)->getProperty<std::string>(proxyKey, i)));
      }
    }
    return true;
}

/* virtual */ bool
SkeletonMapper::configRemove(jccl::ConfigElementPtr element)
{
    TRACE_FUNC;

    // XXX TODO: clear jointMap_ ?

    return false;
}

void
SkeletonMapper::applyBone(Ogre::Bone* bone)
{
    BoneProxyNameMap::const_iterator bpnIt = boneProxyNames_.find(bone->getName());

    if(bpnIt != boneProxyNames_.end())
    {
        PositionMap::const_iterator pmIt = positions_.find((*bpnIt).second);

        if(pmIt != positions_.end())
        {
            Ogre::Vector3    jtPosition;
            Ogre::Vector3    jtScale;
            Ogre::Quaternion jtOrientation;
            Ogre::Matrix4    jtMatrix = 
                            MatrixUtils::fromGMTL((*(*pmIt).second)->getData(gadget::PositionUnitConversion::ConvertToMeters));
            
            jtMatrix.decomposition(jtPosition,jtScale,jtOrientation);
            
            bone->resetOrientation();     
            jtOrientation = bone->convertWorldToLocalOrientation(jtOrientation);
            bone->setOrientation(jtOrientation); 

            if(bone->getName() == std::string("Root"))
            {
              bone->setPosition(jtPosition);
#if 1            
            printf("bone........[%s]\nposition....[%f,%f,%f]\norientation.[%f,%f,%f,%f]\n",
                    bone->getName().c_str(),
                    jtPosition.x,
                    jtPosition.y,
                    jtPosition.z,
                    jtOrientation.w,
                    jtOrientation.x,
                    jtOrientation.y,
                    jtOrientation.z);
#endif
            }
            

        }
    }

    Ogre::Node::ChildNodeIterator cIt = bone->getChildIterator();

    for(; cIt.hasMoreElements(); cIt.moveNext())
    {
        applyBone(dynamic_cast<Ogre::Bone*>(cIt.peekNextValue()));
    }
}

void
SkeletonMapper::initJointMap(void)
{
    // clear previous position proxies
    PositionMap::iterator pmIt  = positions_.begin();
    PositionMap::iterator pmEnd = positions_.end  ();

    for(; pmIt != pmEnd; ++pmIt)
        delete (*pmIt).second;

    positions_.clear();

    if(skel_.get() == NULL)
        return;

    // find all position proxies used by bones
    BoneProxyNameMap::const_iterator bpnIt  = boneProxyNames_.begin();
    BoneProxyNameMap::const_iterator bpnEnd = boneProxyNames_.end  ();

    for(; bpnIt != bpnEnd; ++bpnIt)
    {
        printf("loading[%s]\n",(*bpnIt).second.c_str());
        positions_.insert(PositionMap::value_type((*bpnIt).second, NULL));
    }

    // create PositionInterfaces
    pmIt  = positions_.begin();
    pmEnd = positions_.end  ();

    for(; pmIt != pmEnd; ++pmIt)
    {
        (*pmIt).second = new gadget::PositionInterface();
        ((*pmIt).second)->init((*pmIt).first);
    }
}
