#include <iostream>

class Doctor{
    public:
    Doctor(const std::string& name);
    std::string toString();

    private:
        std::string theName;
};

//the arguments in the initialization list are used as constructor arguments for the various data members
//copy constructor -item4
Doctor::Doctor(const std::string& name)
:theName(name)
{}
std::string Doctor::toString(){
    return "nume doctor: " + theName;
}
//nu stiam daca un obiect de tip Doctor a fost initializat cand apelam toString pe el din Patient
//facand asa stim ca atunci cand apelam toString se initializeaza un object de tip Doctor

Doctor& doc(){
    static Doctor doc("Doc Mihai");
    return doc;
}

class Patient{
    public:
    Patient(const std::string& name, const int patientId);
    std::string toString();

    private:
        std::string theName;
        int thePatientId;
};
//the arguments in the initialization list are used as constructor arguments for the various data members
// -item4
Patient::Patient(const std::string& name, const int patientId)
:theName(name),
thePatientId(patientId)
{}
std::string Patient::toString(){
    return "pacient -> nume: "+theName+ ", id: "+std::to_string(thePatientId)+", doctor -> " + doc().toString();
}

class City{

};

class Clinic{
    public:
    Clinic(const std::string& name, const int clinicId);

    private:
    std::string theName;
    int theClinicId;
    Clinic(const Clinic&);
    Clinic& operator=(const Clinic&);
};
Clinic::Clinic(const std::string& name, const int clinicId)
:theName(name),
theClinicId(clinicId)
{}


int main(){
    //item 4
    int i;
    std::cout<<i<<"\n";

    Patient p1("Ana", 198);
    std::cout<<(p1.toString())<<"\n";

    //item 5
    //compilatorul creaza constructorul automat pentru ca are nevoie de el
    //daca am fi declarat noi prin suprascriere constructorul, compilatorul nu ar fi creat altul default
    City c;
    c.~City();

    //copy constr creat de compilator
    Patient p2(p1);
    std::cout<<(p2.toString())<<"\n";

    //copy assignment creat de compilator automat
    Patient p3 = p1;
    std::cout<<(p3.toString())<<"\n";

    //descructorul a fost creat automat de asemenea
    p2.~Patient();
    p3.~Patient();

    //item 6
    //copy constr si copy assignment operator sunt declarate private => nu pot fi accesate
    Clinic c1("dentalmed", 12345);
    //Clinic c2 = c1;
    //Clinic c3(c1);
    c1.~Clinic();

    return 0;
}