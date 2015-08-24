//n is power of 2
void FWT_And(int x[], int l, int r, int v) //FWT v = 1, DFWT v = -1
{
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	FWT_And(x, l, mid, v);
	FWT_And(x, mid + 1, r, v);
	for (int i = 0; i <= mid - l; i++)
		x[i + l] += x[mid + i + 1] * v;
}
void FWT_Or(int x[], int l, int r, int v) // FWT v = 1 DFWT v = -1
{
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	FWT_Or(x, l, mid, v);
	FWT_Or(x, mid + 1, r, v);
	for (int i = 0; i <= mid - l; i++)
		x[mid + i + 1] += x[l + i] * v;
}
void FWT_Xor(int x[], int l, int r)
{
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	FWT_Xor(x, l, mid);
	FWT_Xor(x, mid + 1, r);
	for (int i = 0; i <= mid - l; i++)
		x[l + i] +=  x[mid + i + 1], x[mid + i + 1] = x[l + i] - 2 * x[mid + i + 1]; 
}
void DFWT_Xor(int x[], int l, int r)
{
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	DFWT_Xor(x, l, mid);
	DFWT_Xor(x, mid + 1, r);
	for (int i = 0; i <= mid - l; i++)
		x[l + i] = (x[l + i] + x[mid + i + 1]) / 2, x[mid + i + 1] = x[l + i] - x[mid + i + 1]; 
}
