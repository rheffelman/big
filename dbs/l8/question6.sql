SELECT Student.first, Student.last
FROM Student
WHERE (Student.age >= 21)

INTERSECT

SELECT Student.first, Student.last
FROM Section, Student, StudentTakesSection, Professor
WHERE Student.ssn = StudentTakesSection.ssn
AND Section.sectionID = StudentTakesSection.sectionID
AND Section.professorID = 1