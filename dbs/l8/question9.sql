SELECT DISTINCT course.name
FROM Course, Section, Student, StudentTakesSection
WHERE Course.courseID = Section.courseID
AND section.sectionID = StudentTakesSection.sectionID
AND studentTakesSection.ssn = Student.ssn
AND StudentTakesSection.ssn = Student.ssn
AND Student.age = (SELECT max(age) FROM Student);
