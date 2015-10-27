#ifndef _RUNNER_
#define _RUNNER_

class Runner {
    private:
        
    public:
        virtual bool run(bool) = 0;
        virtual void test(){};
        virtual ~Runner(){};
};

#endif
