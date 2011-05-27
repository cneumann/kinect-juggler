
#ifndef OGREUTILS_HPP_GUARD
#define OGREUTILS_HPP_GUARD

#include <gmtl/Matrix.h>
#include <vrj/Display/Frustum.h>

#include <OGRE/OgreMatrix4.h>

#include <vector>

namespace MatrixUtils
{
  Ogre::Matrix4   fromGMTL(gmtl::Matrix44f const& m);
  gmtl::Matrix44f fromOGRE(Ogre::Matrix4 const&   m);

  Ogre::Matrix4   makeFrustumMatrix(vrj::Frustum const& frustum);

} // namespace MatrixUtils

#endif // OGREUTILS_HPP_GUARD
