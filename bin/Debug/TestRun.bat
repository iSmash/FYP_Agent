FOR %%F IN (B, C, D, Z) DO (
	FOR /L %%M IN (0,1,3) DO (
		FOR /L %%R IN (1,1,3) DO (
			Echo %%F %%M %%R
			FYP.exe %%F %%M
			)
		)
	)
