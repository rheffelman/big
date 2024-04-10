SELECT DISTINCT Professor.first, Professor.last
FROM Professor, Section
WHERE Section.professorID = Professor.professorID
AND Section.courseID = 2