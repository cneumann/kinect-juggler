
#include "VRJOgreApp.hpp"

#include <gadget/Type/Position/PositionUnitConversion.h>

#include <OGRE/OgreLog.h>
#include <OGRE/OgreRoot.h>

#include <vpr/Util/Debug.h>

namespace
{
    Ogre::String const ogreLogName("VRJOgreApp.log");

    class VPROgreLogListener : public Ogre::LogListener
    {
      public:
        virtual void messageLogged(Ogre::String const&   message,
                                   Ogre::LogMessageLevel lml,
                                   bool                  maskDebug,
                                   Ogre::String const&   logName  );
    };

    /* virtual */ void
    VPROgreLogListener::messageLogged(Ogre::String const&   message,
                                      Ogre::LogMessageLevel lml,
                                      bool                  maskDebug,
                                      Ogre::String const&   logName  )
    {
        if(logName == ogreLogName)
        {
            switch(lml)
            {
            case Ogre::LML_TRIVIAL:
            {
                vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
                    << message << vprDEBUG_FLUSH;
            }
            break;

            case Ogre::LML_NORMAL:
            {
                vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
                    << message << vprDEBUG_FLUSH;
            }
            break;

            case Ogre::LML_CRITICAL:
            {
                vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
                    << message << vprDEBUG_FLUSH;
            }
                break;
            }
        }
    }

    VPROgreLogListener ogreLogListener;
}


/* virtual */ void
VRJOgreApp::init(void)
{
}

/* virtual */ void
VRJOgreApp::apiInit(void)
{
    root_ = new Ogre::Root();
    log_  = Ogre::LogManager::getSingleton().createLog(ogreLogName,
                                                       false,
                                                       true,
                                                       true);
    log_->addListener(&ogreLogListener);

    Ogre::RenderSystemList const&          rsList = root_->getAvailableRenderers();
    Ogre::RenderSystemList::const_iterator rsIt   = rsList.begin();
    
    for(std::size_t i = 0; rsIt != rsList.end(); ++rsIt, ++i)
    {
        std::ostringstream oss;
        oss << i << ": " << (*rsIt)->getName();

        log_->logMessage(oss.str());
    }
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
    log_->removeListener(&ogreLogListener);

    delete log_;
    log_ = NULL;

    delete root_;
    root_ = NULL;
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
VRJOgreApp::VRJOgreApp(vrj::Kernel* kernel)
    : vrj::opengl::App  (kernel),
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
