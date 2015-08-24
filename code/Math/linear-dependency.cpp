for(int i = 0;i < n;i++) {
	for(int j = 31;j >= 0;j--) {
		if(xx[i] & (1LL<<j)) {
			if(!ind[j]) { ind[j] = xx[i]; break; }
			else xx[i] ^= ind[j];
		}
	}
}