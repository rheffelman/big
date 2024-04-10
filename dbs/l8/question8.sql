SELECT Course.name, Section.sectionID
FROM Course, Section, Department, Professor
WHERE Professor.professorID = Department.chair --Professor is chair
AND Section.professorID = Professor.professorID --Professor taught course
AND Section.courseID = Course.courseID --Section number of course is real
AND Course.deptID = Department.deptID --Course is part of department