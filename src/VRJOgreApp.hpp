
#include <boost/noncopyable.hpp>

#include <vrj/Draw/OpenGL/App.h>


class VRJOgreApp : public vrj::opengl::App,
                   private boost::noncopyable
{
  public:
    virtual void  init           (void);
    virtual void  apiInit        (void);
    virtual void  contextInit    (void);

    virtual void  preFrame       (void);
    virtual void  latePreFrame   (void);
    virtual void  intraFrame     (void);      // called in parallel to the draw functions
    virtual void  bufferPreDraw  (void);      // called for each draw buffer
    virtual void  contextPreDraw (void);      // called for each context

    virtual void  draw           (void) = 0;  // called for each viewport
    
    virtual void  contextPostDraw(void);      // called for each context
    virtual void  postFrame      (void);
    
    virtual void  contextClose   (void);
    virtual void  exit           (void);

    virtual float getDrawScaleFactor(void);
    virtual bool  configCanHandle   (jccl::ConfigElementPtr cfg);

  protected:
    explicit  VRJOgreApp(void);
    virtual  ~VRJOgreApp(void) = 0;

    virtual bool  configAdd   (jccl::ConfigElementPtr cfg);
    virtual bool  configRemove(jccl::ConfigElementPtr cfg);
};
