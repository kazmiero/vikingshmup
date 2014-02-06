#ifndef PROGRAMCONSTANTS_H
#define PROGRAMCONSTANTS_H

#include <string>

class ProgramConstants
{
    public:
        static ProgramConstants& getInstance();

        const float getFps() const;
        const int getCameraWidth() const;
        const int getCameraHeight() const;
        const std::string& getSpritesDir() const;
        const std::string& getMenusDir() const;

    private:
        ProgramConstants();
        static ProgramConstants* instance_;
        virtual ~ProgramConstants();

        // todo!
        bool initFromFile(const std::string& filename);

        const float fps_;
        const int cameraWidth_, cameraHeight_;
        const std::string spritesDir_, menusDir_;
};

#endif // PROGRAMCONSTANTS_H
