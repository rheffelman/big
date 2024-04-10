SELECT Course.name, Section.sectionID
FROM Course, Section
WHERE Section.courseID = Course.courseID
AND Course.deptID = 1