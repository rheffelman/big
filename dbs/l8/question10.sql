SELECT Course.name, Section.sectionID
FROM Student, StudentTakesSection, Section, Course
WHERE Student.ssn = StudentTakesSection.ssn
AND Section.sectionID = StudentTakesSection.sectionID
AND Section.courseID = Course.courseID
GROUP BY Section.sectionID
HAVING AVG(Student.age)
ORDER BY AVG(Student.age)  ASC -- lower averages on top, higher on bottom
LIMIT 1 -- only select the top row