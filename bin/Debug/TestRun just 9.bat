FOR %%F IN (z) DO (
	FOR  %%M IN (9) DO (
		FOR /L %%R IN (1,1,3) DO (
			FYP.exe %%F %%M
			)
		)
	)
