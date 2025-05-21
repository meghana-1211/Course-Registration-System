#  Course Registration System - IIT Madras

This is an object-oriented **Course Registration System** designed for IIT Madras. The system enables students to enroll in courses, manages student and course records, handles waitlists, and ensures prerequisite and scheduling constraints are met.

---

##  Features

###  Core Functionality
- **Student Management**
  - Unique Student ID
  - Student name and year of study
  - Tracks completed and currently enrolled courses

- **Course Management**
  - Unique course code, course name
  - Credit information
  - Maximum capacity
  - Prerequisite handling
  - Time slot allocation (e.g., Slot A, Slot B)

- **Enrollment System**
  - Validates prerequisites
  - Avoids time slot clashes
  - Prevents duplicate enrollments

###  Enhanced Features (Part 2)
- **Waitlist Management**
  - When a course is full, students are placed on a **First-Come-First-Serve (FCFS)** waitlist.
  - Students can be on multiple waitlists.

- **Drop Functionality**
  - Students can drop a course.
  - When dropped, the system automatically processes the waitlist for that course and enrolls the next eligible student.

- **Cycle Detection in Prerequisites**
  - Prevents adding a course if it introduces a **cyclic dependency** in prerequisites.
  - Ensures the integrity of course prerequisites using graph cycle detection.

---

##  Input Format

### General Format
- First line contains an integer `Q` - number of operations to perform.

### Student/Course Operations
- Add Student: `add_student <student_id> <name> <year>`
- Add Course: `add_course <course_code> <course_name> <credits> <capacity> <prerequisites> <slot>`
- Enroll: `enroll <student_id> <course_code>`
- Drop: `drop <student_id> <course_code>`

>  For `drop` operation:
> - If student or course does not exist, the system ignores the request.

---

##  Example Operations
```plaintext
add_student S001 Alice 2
add_course CS101 "Intro to CS" 3 2 [] SlotA
add_course CS102 "Data Structures" 3 2 [CS101] SlotB
enroll S001 CS101
enroll S001 CS102
drop S001 CS101
