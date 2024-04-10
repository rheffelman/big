SELECT Course.name, Section.sectionID, COUNT(*) AS enrollment
FROM Course, Section, StudentTakesSection
WHERE Course.courseID = Section.courseID
AND Section.sectionID = StudentTakesSection.sectionID
GROUP BY Section.sectionID
HAVING COUNT(*) = (
	SELECT COUNT(*) 
	FROM StudentTakesSection
	GROUP BY StudentTakesSection.sectionID
	ORDER BY COUNT(*) -- puts in ascending order
	LIMIT 1 -- selects first column
)
ORDER BY Course.name, Section.sectionID