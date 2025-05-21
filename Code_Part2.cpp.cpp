#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
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
    queue<string> Waiting_list;
};
bool hasCycle(const string& course_code, unordered_map<string, Course>& Courses, unordered_set<string>& completed, unordered_set<string>& stack) {
    if (stack.find(course_code) != stack.end()) {return true; }
    if (completed.find(course_code) != completed.end()) { return false;}
    completed.insert(course_code);
    stack.insert(course_code);
    for (const auto& prerequisite : Courses[course_code].Prerequisites) {
        if (Courses.find(prerequisite) != Courses.end() && hasCycle(prerequisite, Courses, completed, stack)) {
            return true;
        }
    }
    stack.erase(course_code);
    return false;
}
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
            if (prerequisite_courses_exist) {
                    unordered_set<string> completed;
                    unordered_set<string> stack;
                    Courses[Course_code] = temp_course;  
                    if (hasCycle(Course_code, Courses, completed, stack)) {Courses.erase(Course_code); } 
                    else {Courses[Course_code] = temp_course;}
            }
        }
        else if(temp=="enroll"){
            string temp_id;
            string temp_course_code;
            cin>>temp_id>>temp_course_code;
            if(Students.find(temp_id)==Students.end()){continue;}
            if(Courses.find(temp_course_code)==Courses.end()){continue;}
            if(find(Students[temp_id].Enrolled_courses.begin(),Students[temp_id].Enrolled_courses.end(),temp_course_code)!=Students[temp_id].Enrolled_courses.end()){continue;}
            if(Courses[temp_course_code].Students_enrolled.size()==Courses[temp_course_code].Capacity){
                Courses[temp_course_code].Waiting_list.push(temp_id);
                continue;
            }
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
        else if(temp=="drop"){
            string temp_id;
            string temp_course_code;
            cin>>temp_id>>temp_course_code;
            if (Courses.find(temp_course_code) == Courses.end() || Students.find(temp_id) == Students.end()) {continue;}
            Courses[temp_course_code].Students_enrolled.erase(remove(Courses[temp_course_code].Students_enrolled.begin(),Courses[temp_course_code].Students_enrolled.end(),temp_id),Courses[temp_course_code].Students_enrolled.end());
            Students[temp_id].Enrolled_courses.erase(remove(Students[temp_id].Enrolled_courses.begin(),Students[temp_id].Enrolled_courses.end(),temp_course_code),Students[temp_id].Enrolled_courses.end());
            while(!Courses[temp_course_code].Waiting_list.empty()){
                bool no_conflicting_slots=true;
                bool required_prerequisites=true;
                for(int i=0;i<Students[Courses[temp_course_code].Waiting_list.front()].Enrolled_courses.size();i++){
                    if(Courses[Students[Courses[temp_course_code].Waiting_list.front()].Enrolled_courses[i]].Time_slot==Courses[temp_course_code].Time_slot){
                        no_conflicting_slots=false;
                        break;
                    }
                }
                for(int i=0;i<Courses[temp_course_code].Prerequisites.size();i++){
                    if(find(Students[Courses[temp_course_code].Waiting_list.front()].Completed_courses.begin(),Students[Courses[temp_course_code].Waiting_list.front()].Completed_courses.end(),Courses[temp_course_code].Prerequisites[i])==Students[Courses[temp_course_code].Waiting_list.front()].Completed_courses.end()){
                        required_prerequisites=false;
                        break;
                    }
                }
                if(no_conflicting_slots&&required_prerequisites){
                    Students[Courses[temp_course_code].Waiting_list.front()].Enrolled_courses.push_back(temp_course_code);
                    Courses[temp_course_code].Students_enrolled.push_back(Courses[temp_course_code].Waiting_list.front());
                }
                else{
                    Courses[temp_course_code].Waiting_list.pop();
                }
            }
        }
    }
}