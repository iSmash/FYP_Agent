FOR %%F IN (B, C, D, E, Z) DO (
	FOR  %%M IN (0,1,2,3,6) DO (
		FOR /L %%R IN (1,1,3) DO (
			FYP.exe %%F %%M
			)
		)
	)
