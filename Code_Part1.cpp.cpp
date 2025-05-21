#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Student{
    public:
    string Name;
    int Year_of_study;
    vector<string> Completed_courses;
    vector<string> Enrolled_courses;
};
class Course{
    public:
    string Course_name;
    int No_of_credits;
    int Capacity;
    char Time_slot;
    vector<string> Students_enrolled;
    vector<string> Prerequisites;
};

int main(){
    int n;
    cin>>n;
    string temp;
    unordered_map<string,Student> Students;
    unordered_map<string,Course> Courses;
    while(n--){
        cin>>temp;
        if(temp=="add_student"){
            string ID;
            int no_of_completed_courses;
            Student temp_student;
            cin>>ID>>temp_student.Name>>temp_student.Year_of_study>>no_of_completed_courses;
            for(int i=0;i<no_of_completed_courses;i++){
                string temp_course;
                cin>>temp_course;
                temp_student.Completed_courses.push_back(temp_course);
            }
            Students[ID]=temp_student;
        }
        else if(temp=="add_course"){
            string Course_code;
            int no_of_prerequisites;
            Course temp_course;
            cin>>Course_code>>temp_course.Course_name>>temp_course.No_of_credits>>temp_course.Capacity>>temp_course.Time_slot>>no_of_prerequisites;
            for(int i=0;i<no_of_prerequisites;i++){
                string temp_prerequisite;
                cin>>temp_prerequisite;
                temp_course.Prerequisites.push_back(temp_prerequisite);
            }
            bool prerequisite_courses_exist=true;
            for(int i=0;i<no_of_prerequisites;i++){
                if(Courses.find(temp_course.Prerequisites[i])==Courses.end()){
                    prerequisite_courses_exist=false;
                    break;
                }
            }
            if(prerequisite_courses_exist){
            Courses[Course_code]=temp_course;
            }
        }
        else if(temp=="enroll"){
            string temp_id;
            string temp_course_code;
            cin>>temp_id>>temp_course_code;
            if(Students.find(temp_id)==Students.end()){continue;}
            if(Courses.find(temp_course_code)==Courses.end()){continue;}
            if(Courses[temp_course_code].Students_enrolled.size()==Courses[temp_course_code].Capacity){continue;}
            if(find(Students[temp_id].Enrolled_courses.begin(),Students[temp_id].Enrolled_courses.end(),temp_course_code)!=Students[temp_id].Enrolled_courses.end()){continue;}
            bool no_conflicting_slots=true;
            bool required_prerequisites=true;
            for(int i=0;i<Students[temp_id].Enrolled_courses.size();i++){
                if(Courses[Students[temp_id].Enrolled_courses[i]].Time_slot==Courses[temp_course_code].Time_slot){
                    no_conflicting_slots=false;
                    break;
                }
            }
            for(int i=0;i<Courses[temp_course_code].Prerequisites.size();i++){
                if(find(Students[temp_id].Completed_courses.begin(),Students[temp_id].Completed_courses.end(),Courses[temp_course_code].Prerequisites[i])==Students[temp_id].Completed_courses.end()){
                    required_prerequisites=false;
                    break;
                }
            }
            if(no_conflicting_slots&&required_prerequisites){
            Students[temp_id].Enrolled_courses.push_back(temp_course_code);
            Courses[temp_course_code].Students_enrolled.push_back(temp_id);
            }
        }
        else if(temp=="print"){
            string temp_course_code;
            cin>>temp_course_code;
            if(Courses.find(temp_course_code)==Courses.end()){
                cout<<"Invalid Course "<<temp_course_code<<endl;
            }
            else{
                cout<<"Enrolled students in "<<temp_course_code<<":"<<endl;
                for(int i=0;i<Courses[temp_course_code].Students_enrolled.size();i++){
                    cout<<Courses[temp_course_code].Students_enrolled[i]<<" ";
                }
                cout<<endl;
            }

        }
    }
}