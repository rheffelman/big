SELECT DISTINCT Student.first, Student.last
FROM Student, Department, Professor, Section, StudentTakesSection
WHERE Student.ssn = StudentTakesSection.ssn
AND Section.sectionID = StudentTakesSection.sectionID
AND Section.professorID = Professor.professorID
AND Professor.professorID = Department.chair