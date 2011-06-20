
#ifndef SKELETONMAPPER_HPP_GUARD
#define SKELETONMAPPER_HPP_GUARD

#include <gadget/Type/PositionInterface.h>

#include <OGRE/OgreSkeleton.h>

#include <tr1/unordered_map>

// forward declarations

namespace Ogre
{
    class Bone;
} // namespace Ogre

class SkeletonMapper : public jccl::ConfigElementHandler
{
  public:
    explicit SkeletonMapper(Ogre::Skeleton* skel);

    void            setSkeleton(Ogre::Skeleton* skel);
    Ogre::Skeleton* getSkeleton(void                );

    void apply(void);

    static  bool classConfigCanHandle(jccl::ConfigElementPtr element);
    virtual bool configCanHandle     (jccl::ConfigElementPtr element);
    virtual bool configAdd           (jccl::ConfigElementPtr element);
    virtual bool configRemove        (jccl::ConfigElementPtr element);

  protected:
    typedef std::tr1::unordered_map<std::string, gadget::PositionInterface*> PositionMap;
    typedef std::tr1::unordered_map<std::string, std::string>                BoneProxyNameMap;

    void initJointMap(void);
    void applyBone   (Ogre::Bone* bone);
 
    Ogre::SkeletonPtr  skel_;
    PositionMap        positions_;
    BoneProxyNameMap   boneProxyNames_;
};

#endif // SKELETONMAPPER_HPP_GUARD
