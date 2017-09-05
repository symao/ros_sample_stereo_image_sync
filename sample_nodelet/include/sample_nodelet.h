#ifndef __SAMPLE_NODELET_H__
#define __SAMPLE_NODELET_H__
#include <nodelet/nodelet.h>
namespace example_pkg
{
    class SampleNodelet: public nodelet::Nodelet
    {
    public:
        virtual void onInit();
    };
}
#endif //__SAMPLE_NODELET_H__