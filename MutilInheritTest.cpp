#include <string>
#include <memory>
#include <iostream>

class IPerson {
public:
    virtual ~IPerson() = default;
    virtual std::string name() const = 0;
    virtual std::string birthDate() const = 0;
};

struct DatabaseID {
    std::string idName;
    std::string birthDate;
    unsigned idx;
};

class PersonInfo {
public:
    explicit PersonInfo(DatabaseID pid): pid_(std::move(pid)){}
    virtual ~PersonInfo() = default;
    virtual std::string theName() const;
    virtual std::string theBirthDate() const;
    virtual std::string valueDelimOpen() const;
    virtual std::string valueDelimClose() const;
private:
    DatabaseID pid_;
};

std::string PersonInfo::theName() const {
    return valueDelimOpen() + pid_.idName + valueDelimClose();
}

std::string PersonInfo::theBirthDate() const {
    return valueDelimOpen() + pid_.birthDate + valueDelimClose();
}

std::string PersonInfo::valueDelimOpen() const {
    return "[";
}

std::string PersonInfo::valueDelimClose() const {
    return "]";
}

class CPerson: public IPerson, private PersonInfo {
public:
    explicit CPerson(const DatabaseID &pid) : PersonInfo(pid) {}
    std::string name() const override;
    std::string birthDate() const override;
private:
    std::string valueDelimOpen() const override;
    std::string valueDelimClose() const override;
};

std::string CPerson::name() const {
    return PersonInfo::theName();
}

std::string CPerson::birthDate() const {
    return PersonInfo::theBirthDate();
}

std::string CPerson::valueDelimOpen() const {
    return "{" + PersonInfo::valueDelimOpen();
}

std::string CPerson::valueDelimClose() const {
    return PersonInfo::valueDelimClose() + "}";
}

int main()
{
    DatabaseID pid{"XiaoMing", "1995-01-01", 1};
    std::unique_ptr<IPerson> personOne = std::make_unique<CPerson>(pid);
    std::cout << "personOne:" << personOne->name() <<", " << personOne->birthDate() << std::endl;
    DatabaseID pid2{"XiaoWang", "1994-01-01", 2};
    IPerson &&personTwo = CPerson(pid2);
    std::cout << "personTwo:" << personTwo.name() <<", " <<personTwo.birthDate() << std::endl;
    return 0;
}

//personOne:{[XiaoMing]}, {[1995-01-01]}
//personTwo:{[XiaoWang]}, {[1994-01-01]}













