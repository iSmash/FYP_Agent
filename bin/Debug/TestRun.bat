FOR %%F IN (B, C, D, E, Z) DO (
	FOR /L %%M IN (0,1,3) DO (
		FOR /L %%R IN (1,1,3) DO (
			FYP.exe %%F %%M
			)
		)
	)
