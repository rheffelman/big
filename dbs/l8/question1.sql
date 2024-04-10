SELECT Course.name
FROM Course, Section, Professor
WHERE Course.courseID = Section.sectionID
AND Section.professorID = Professor.professorID