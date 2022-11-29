#include <iostream>

class Doctor{
    public:
    Doctor(const std::string& name);
    std::string toString();

    private:
        std::string theName;
};

//the arguments in the initialization list are used as constructor arguments for the various data members
Doctor::Doctor(const std::string& name)
:theName(name)
{
}
std::string Doctor::toString(){
    return "nume doctor: " + theName;
}

class Patient{
    public:
    Patient(const std::string& name, const int patientId, Doctor& doc);
    Patient& operator=(const Patient&);
    std::string toString();

    private:
        std::string theName;
        int thePatientId;
        Doctor *theDoc;
};
//the arguments in the initialization list are used as constructor arguments for the various data members
// -item4
Patient::Patient(const std::string& name, const int patientId, Doctor& doc)
:theName(name),
thePatientId(patientId),
theDoc(&doc)
{}

//item 11
Patient&Patient::operator=(const Patient& rhs){
    theName = rhs.theName;
    thePatientId = rhs.thePatientId;

    Doctor *dOrig = theDoc;
    theDoc = new Doctor(*rhs.theDoc);
    delete dOrig;

    return *this;
}
std::string Patient::toString(){
    return "patient -> name: "+theName+ ", id: "+ std::to_string(thePatientId) + ", doctor -> " + theDoc->toString();
}

class UrgentPatient:public Patient{
    public:
    UrgentPatient(const std::string& name, const int patientId, Doctor doc, const int priority, const std::string& problemDescription);
    UrgentPatient& operator=(const UrgentPatient& rhs);
    std::string toString();

    private:
    int thePriority;
    std::string theProblemDescription;
};
UrgentPatient::UrgentPatient(const std::string& name, const int patientId, Doctor doc, const int priority, const std::string& problemDescription)
:Patient(name, patientId, doc),
thePriority(priority),
theProblemDescription(problemDescription)
{}

UrgentPatient&UrgentPatient::operator=(const UrgentPatient& rhs){
    Patient::operator=(rhs);
    thePriority = rhs.thePriority;
    theProblemDescription = rhs.theProblemDescription;

    return *this;
}
std::string UrgentPatient::toString(){

    return Patient::toString() + ", priority -> " + std::to_string(thePriority) +", short description -> " + theProblemDescription;
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

//item 10
Clinic&Clinic::operator=(const Clinic&){
    return *this;
}

int main(){
    //item 4
    int i = 2;
    std::cout<<i<<"\n";

    Doctor d1("Popescu");
    Patient p1("Ana", 198, d1);
    std::cout<<(p1.toString())<<"\n";

    //item 5
    //compilatorul creaza constructorul automat pentru ca are nevoie de el
    //daca am fi declarat noi prin suprascriere constructorul, compilatorul nu ar fi creat altul default
    City c;
    c.~City();

    //copy constr creat de compilator
    Patient p2(p1);
    std::cout<<(p2.toString())<<"\n";

    Patient p4("Maria", 200, d1);
    //copy assignmentul creat de mine
    Patient p3 = p4;
    std::cout<<(p3.toString())<<"\n";

    //descructorul a fost creat automat
    p2.~Patient();
    p3.~Patient();
    p4.~Patient();

    // //item 12
    UrgentPatient up1("Delia", 308, (Doctor("Cristescu")), 2, "asthma");
    std::cout<<up1.toString()<<'\n';

    UrgentPatient up2 = up1;
    std::cout<<up2.toString()<<'\n';

    //item 6
    //copy constr si copy assignment operator sunt declarate private => nu pot fi accesate
    Clinic c1("dentalmed", 12345);
    //Clinic c2 = c1;
    //Clinic c3(c1);
    c1.~Clinic();

    return 0;
}