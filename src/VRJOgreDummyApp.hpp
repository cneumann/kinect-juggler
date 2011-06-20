
#ifndef VRJOGREDUMMYAPP_HPP_GUARD
#define VRJOGREDUMMYAPP_HPP_GUARD

#include "VRJOgreApp.hpp"

class VRJOgreDummyApp : public VRJOgreApp
{
  public:
    explicit  VRJOgreDummyApp(vrj::Kernel* kernel);
    virtual  ~VRJOgreDummyApp(void               );

    virtual void contextInit(void);
    virtual void draw       (void);

    virtual bool configCanHandle(jccl::ConfigElementPtr element);
    virtual bool configAdd      (jccl::ConfigElementPtr element);
    virtual bool configRemove   (jccl::ConfigElementPtr element);
};

#endif // VRJOGREDUMMYAPP_HPP_GUARD
