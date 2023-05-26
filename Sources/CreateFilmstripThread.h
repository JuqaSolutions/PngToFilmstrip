#pragma once

struct CreateFilmstripThread : public juce::ThreadWithProgressWindow
{
    CreateFilmstripThread(std::function<void()>& fun)
        : ThreadWithProgressWindow("CreateFilmstripThread", true, true)
        , func(fun)
    {
    }

    void run() override
    {
        DBG("Enter into the thread");
        //std::cout<<"Enter into the thread"<<std::endl;
        func();
        DBG("end of thread");
        //std::cout<<"end of thread"<<std::endl;
    }

private:
    std::function<void()>& func;
};