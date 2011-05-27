
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
};

#endif // VRJOGREDUMMYAPP_HPP_GUARD
