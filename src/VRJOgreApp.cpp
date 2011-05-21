
#include "VRJOgreApp.hpp"

#include <gadget/Type/Position/PositionUnitConversion.h>

/* virtual */ void
VRJOgreApp::init(void)
{
}

/* virtual */ void
VRJOgreApp::apiInit(void)
{
}

/* virtual */ void
VRJOgreApp::contextInit(void)
{
}

/* virtual */ void
VRJOgreApp::preFrame(void)
{
}

/* virtual */ void
VRJOgreApp::latePreFrame(void)
{
}

/* virtual */ void
VRJOgreApp::intraFrame(void)
{
}

/* virtual */ void
VRJOgreApp::bufferPreDraw(void)
{
}

/* virtual */ void
VRJOgreApp::contextPreDraw(void)
{
}

/* virtual */ void
VRJOgreApp::draw(void)
{
}

/* virtual */ void
VRJOgreApp::contextPostDraw(void)
{
}

/* virtual */ void
VRJOgreApp::postFrame(void)
{
}

/* virtual */ void
VRJOgreApp::contextClose(void)
{
}

/* virtual */ void
VRJOgreApp::exit(void)
{
}

/* virtual */ float
VRJOgreApp::getDrawScaleFactor(void)
{
    return gadget::PositionUnitConversion::ConvertToMeters;
}

/* virtual */ bool
VRJOgreApp::configCanHandle(jccl::ConfigElementPtr cfg)
{
    return false;
}

/* explicit */
VRJOgreApp::VRJOgreApp(void)
    : vrj::opengl::App  (),
      boost::noncopyable()
{
}

/* virtual */
VRJOgreApp::~VRJOgreApp(void)
{
}

/* virtual */ bool
VRJOgreApp::configAdd(jccl::ConfigElementPtr cfg)
{
    return false;
}

/* virtual */ bool
VRJOgreApp::configRemove(jccl::ConfigElementPtr cfg)
{
    return false;
}
