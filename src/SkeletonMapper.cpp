
#include "SkeletonMapper.hpp"

// system header

#include <OGRE/OgreBone.h>

// project header

/* explicit */
SkeletonMapper::SkeletonMapper(Ogre::Skeleton* skel)
    : jccl::ConfigElementHandler(),
      skel_                     (skel),
      positions_                (),
      boneProxyNames_           ()
{
}

void
SkeletonMapper::setSkeleton(Ogre::Skeleton* skel)
{
    skel_ = Ogre::SkeletonPtr(skel);

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

/* virtual */ bool
SkeletonMapper::configCanHandle(jccl::ConfigElementPtr element)
{
    // XXX TODO: recognize config element

    return false;
}

/* virtual */ bool
SkeletonMapper::configAdd(jccl::ConfigElementPtr element)
{
    // XXX TODO: evaluate configuration
    //           should map OpenNI joint -> OGRE bone handle, store in jointMap_

    return false;
}

/* virtual */ bool
SkeletonMapper::configRemove(jccl::ConfigElementPtr element)
{
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
            // XXX TODO
            // read value from (*pmIt).second and write to bone
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
    // clear previos position proxies
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
        positions_.insert(PositionMap::value_type((*bpnIt).second, NULL));
    }

    // create PositionInterfaces
    pmIt  = positions_.begin();
    pmEnd = positions_.end  ();

    for(; pmIt != pmEnd; ++pmIt)
    {
        (*pmIt).second = new gadget::PositionInterface();
    }
}
