#include <string>
#include <iostream>

class AirPort {

public:
    explicit AirPort(std::string name) : name_(std::move(name)) {
    }
    [[nodiscard]] const std::string &getName() const {
        return name_;
    }

private:
    std::string name_;
};

class AirPlane {
public:
    virtual void fly(const AirPort& destination) = 0;
};

void AirPlane::fly(const AirPort &destination) {
    std::cout << "fly to destination " << destination.getName() << std::endl;
}

class ModelA : public AirPlane {
    void fly(const AirPort &destination) override {
        std::cout << "ModelA:" << std::endl;
        AirPlane::fly(destination);
    }
};

class ModelB : public AirPlane {
    void fly(const AirPort &destination) override {
        std::cout << "ModelB:" << std::endl;
        AirPlane::fly(destination);
    }
};

class ModelC : public AirPlane {
    void fly(const AirPort &destination) override {
        std::cout << "ModelC specific fly to destination " << destination.getName() << std::endl;
    }
};

int main()
{
    AirPort airPort("shanghai");
    AirPlane&& airPlaneA = ModelA();
    AirPlane&& airPlaneB = ModelB();
    AirPlane&& airPlaneC = ModelC();
    airPlaneA.fly(airPort);
    airPlaneB.fly(airPort);
    airPlaneC.fly(airPort);
    return 0;
}

/*
 * Output:
    ModelA:
    fly to destination shanghai
    ModelB:
    fly to destination shanghai
    ModelC specific fly to destination shanghai
 */
