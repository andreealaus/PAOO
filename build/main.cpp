//git repo: https://github.com/andreealaus/PAOO.git
#include <iostream>
#include <memory>
using namespace std;
class Doctor{
    public:
    //default constructor
    Doctor(void); 
    Doctor(const std::string& name, const std::string& spec);
    std::string toString();
    //Item 13
    Doctor* createDoctor();

    void setDoctorSpecialization(std::string spec){
        this->theSpec = spec;
    }
    std::string getSpecialisation(){
        return this->theSpec;
    }

    private:
        std::string theName;
        std::string theSpec;
};

//the arguments in the initialization list are used as constructor arguments for the various data members
Doctor::Doctor(const std::string& name, const std::string& spec)
:theName(name),
theSpec(spec)
{
}
//default constructor
Doctor::Doctor()
:theName(),
theSpec()
{
}

std::string Doctor::toString(){
    return "nume doctor: " + theName;
}

//item 13
Doctor* createDoctor(){
    return (new Doctor);
}

//item 13
int noRAII(){
    Doctor *d = createDoctor();
    d->setDoctorSpecialization("ortoped");
    if (d->getSpecialisation() == "") return -1;
    std::cout<<"got to delete\n";
    delete d;
    return 0;
}

//item 14
class DoctorAvailable{
    private:
        string theName;
        bool available = true;
    public:

    DoctorAvailable(string name){
        this->theName = name;
    }

    DoctorAvailable(const DoctorAvailable &d){
        this->theName = d.theName;
        this->available = d.available;
    }

    ~DoctorAvailable(){
        cout<<"Doctor unavailable deleted"<<"\n";
    }

    string getName(){
        return this->theName;
    }

    bool getAvailability(){
        return this->available;
    }

    void setAvailability(bool availability){
        this->available = availability;
    }

    void isDoctorAvailable(){
        if(this->available == false) 
            cout<<"The doctor "<< this->theName <<" is not available at the moment"<<"\n";
        else
            cout<<"The doctor "<<this->theName<<"is available"<<"\n";
    }

};

void lock(DoctorAvailable &d){
    d.setAvailability(false);
}

void unlock(DoctorAvailable &d){
    d.setAvailability(true);
}

class LockUnavailableDoctor{
    private:
        DoctorAvailable &doctor;
    
    public:
    LockUnavailableDoctor(DoctorAvailable &d):
    doctor(d){
        lock(doctor);
    }

    ~LockUnavailableDoctor(){
        unlock(doctor);
    }

};

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

    Doctor d1("Popescu", "cardiolog");
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
    UrgentPatient up1("Delia", 308, (Doctor("Cristescu", "pneumolog")), 2, "asthma");
    std::cout<<up1.toString()<<'\n';

    UrgentPatient up2 = up1;
    std::cout<<up2.toString()<<'\n';

    //item 6
    //copy constr si copy assignment operator sunt declarate private => nu pot fi accesate
    Clinic c1("dentalmed", 12345);
    //Clinic c2 = c1;
    //Clinic c3(c1);
    c1.~Clinic();

    //item 13
    cout<<'\n';
    auto_ptr<Doctor> d2(createDoctor());
    d2->setDoctorSpecialization("reumatolog");
    auto_ptr<Doctor> d3(d2);
    cout<<d3->getSpecialisation()<<"\n"; //d2 is now NULL -> segmentation fault
    
    shared_ptr<Doctor> d4(createDoctor());
    d4->setDoctorSpecialization("oftalmolog");
    shared_ptr<Doctor> d5;
    d5 = d4;
    cout<<d4->getSpecialisation()<<"\n";       //both f4 and f5 now point to the object
    cout<<d5->getSpecialisation()<<"\n";        //shared_ptr and auto_ptr release resources in their destructors -> prevent resource leaks


    //noRAII();
    //the delete statement isn't reached

    //Item 14

    DoctorAvailable doctorAvailable("Doctorescu");
    doctorAvailable.isDoctorAvailable();
    cout<<"\n";

    LockUnavailableDoctor lock(doctorAvailable); //now the doctor should be unavailable
    doctorAvailable.isDoctorAvailable();
    cout<<"\n";


    return 0;
}