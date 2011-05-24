
#include "VRJOgreApp.hpp"

#include <gadget/Type/Position/PositionUnitConversion.h>
#include <jccl/Config/ConfigElement.h>
#include <vpr/Util/Debug.h>

#include <OGRE/OgreLog.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreRoot.h>


namespace
{
    vpr::DebugCategory const vprDBG_OGRE     (vpr::GUID("f4847549-1eb7-42c5-8c7a-d8092df89fa5"),
                                              "DBG_OGRE", "OGRE: ");
    Ogre::String const       ogreLogName     ("VRJOgreApp.log");
    Ogre::String const       ogreRenderSystem("OpenGL Rendering Subsystem");

    /* Log listener to route OGRE log through VRJuggler logging system.
     */
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
                vprDEBUG(vprDBG_OGRE, vprDBG_VERB_LVL)
                    << message << "\n" << vprDEBUG_FLUSH;
            }
            break;

            case Ogre::LML_NORMAL:
            {
                vprDEBUG(vprDBG_OGRE, vprDBG_WARNING_LVL)
                    << message << "\n" << vprDEBUG_FLUSH;
            }
            break;

            case Ogre::LML_CRITICAL:
            {
                vprDEBUG(vprDBG_OGRE, vprDBG_CRITICAL_LVL)
                    << message << "\n" << vprDEBUG_FLUSH;
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
    // setup logging
    Ogre::LogManager* logMgr = new Ogre::LogManager();
    Ogre::Log*        log    = logMgr->createLog(ogreLogName, true, false, false);
    log->addListener(&ogreLogListener);
}

/* virtual */ void
VRJOgreApp::contextInit(void)
{
    root_ = new Ogre::Root(pluginsConfigFile_);

    Ogre::RenderSystem* rsGL = root_->getRenderSystemByName(ogreRenderSystem);
    assert(rsGL != NULL);

    root_->setRenderSystem(rsGL);

    root_->initialise(false);

    Ogre::NameValuePairList windowOpts;
    windowOpts.insert(Ogre::NameValuePairList::value_type("currentGLContext",  "true"));
    windowOpts.insert(Ogre::NameValuePairList::value_type("externalGLContext", "true"));

    ContextInfo* ctxInfo = &(*contextInfo_);
    ctxInfo->win_ = root_->createRenderWindow("OGRE Render Window", 500, 500, false, &windowOpts);
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
    ContextInfo* ctxInfo = &(*contextInfo_);

    root_->destroyRenderTarget(ctxInfo->win_);
    ctxInfo->win_ = NULL;

    Ogre::Log* log = Ogre::LogManager::getSingleton().getLog(ogreLogName);

    if(log != NULL)
        log->removeListener(&ogreLogListener);

    delete root_;
    root_ = NULL;
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
    bool result(false);

    if(cfg->getID() == "vrjogreapp")
        result = true;

    return result;
}

/* explicit */
VRJOgreApp::VRJOgreApp(vrj::Kernel* kernel)
    : vrj::opengl::App  (kernel),
      boost::noncopyable(),
      pluginsConfigFile_("ogreplugins.cfg"),
      root_             (NULL)
{
}

/* virtual */
VRJOgreApp::~VRJOgreApp(void)
{
}

/* virtual */ bool
VRJOgreApp::configAdd(jccl::ConfigElementPtr cfg)
{
    bool result(true);

    pluginsConfigFile_ = cfg->getProperty<std::string>("plugins_config");

    return result;
}

/* virtual */ bool
VRJOgreApp::configRemove(jccl::ConfigElementPtr cfg)
{
    return false;
}
