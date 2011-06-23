
#ifndef VRJOGREDUMMYAPP_HPP_GUARD
#define VRJOGREDUMMYAPP_HPP_GUARD

#include "VRJOgreApp.hpp"
#include "SkeletonMapper.hpp"

class VRJOgreDummyApp : public VRJOgreApp
{
  public:
    explicit  VRJOgreDummyApp(vrj::Kernel* kernel);
    virtual  ~VRJOgreDummyApp(void               );

    virtual void contextInit    (void);
    virtual void preFrame       (void);
    virtual void draw           (void);
    virtual void postFrame      (void);

    virtual bool configCanHandle(jccl::ConfigElementPtr cfg);  
    virtual bool configAdd      (jccl::ConfigElementPtr element);  
    virtual bool configRemove   (jccl::ConfigElementPtr element);

  private:
    SkeletonMapper  *sklMap_;
    
};

#endif // VRJOGREDUMMYAPP_HPP_GUARD
