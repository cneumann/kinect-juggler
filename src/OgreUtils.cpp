
#include "OgreUtils.hpp"

namespace MatrixUtils
{
    Ogre::Matrix4
    fromGMTL(gmtl::Matrix44f const& m)
    {
        Ogre::Matrix4 result;

        for(std::size_t c = 0; c < 4; ++c)
        {
            for(std::size_t r = 0; r < 4; ++r)
            {
                result[r][c] = m(r, c);
            }
        }

        return result;
    }

    gmtl::Matrix44f
    fromOGRE(Ogre::Matrix4 const& m)
    {
        gmtl::Matrix44f result;

        for(std::size_t c = 0; c < 4; ++c)
        {
            for(std::size_t r = 0; r < 4; ++r)
            {
                result[r][c] = m[r][c];
            }
        }

        return result;
    }

    Ogre::Matrix4
    makeFrustumMatrix(vrj::Frustum const& frustum)
    {
        Ogre::Matrix4 result;

        std::vector<float> const& v = frustum.getValues();

        float n2 = 2.f * v[vrj::Frustum::VJ_NEAR];
        float dx = v[vrj::Frustum::VJ_RIGHT] - v[vrj::Frustum::VJ_LEFT];
        float dy = v[vrj::Frustum::VJ_TOP]   - v[vrj::Frustum::VJ_BOTTOM];
        float dz = v[vrj::Frustum::VJ_FAR]   - v[vrj::Frustum::VJ_NEAR];

        result[0][0] = n2 / dx;
        result[0][1] = 0.f;
        result[0][2] = (v[vrj::Frustum::VJ_RIGHT] + v[vrj::Frustum::VJ_LEFT]) / dx;
        result[0][3] = 0.f;

        result[1][0] = 0.f;
        result[1][1] = n2 / dy;
        result[1][2] = (v[vrj::Frustum::VJ_TOP] + v[vrj::Frustum::VJ_BOTTOM]) / dy;
        result[1][3] = 0.f;

        result[2][0] = 0.f;
        result[2][1] = 0.f;
        result[2][2] = - (v[vrj::Frustum::VJ_FAR] + v[vrj::Frustum::VJ_NEAR]) / dz;
        result[2][3] = - 2.f * v[vrj::Frustum::VJ_FAR] * v[vrj::Frustum::VJ_NEAR] / dz;

        result[3][0] =  0.f;
        result[3][1] =  0.f;
        result[3][2] = -1.f;
        result[3][3] =  0.f;

        return result;
    }

} // namespace MatrixUtils
