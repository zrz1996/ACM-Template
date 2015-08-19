const int maxm = 2000, maxk = 500000; 
struct dancingLinksX
{
    int pt, L[maxk], R[maxk], U[maxk], D[maxk];
    int C[maxk], A[maxk];
    int S[maxm], H[maxm]; 
    int ans[maxm], totAns;
    void init(int m) {
        Fill(H, -1);
        for (int i = 0; i <= m; ++i) S[i] = 0, L[i] = i - 1, R[i] = i + 1, D[i] = U[i] = i;
        L[0] = m, R[m] = 0;
        pt = m;
    }
    inline void insert(int row, int col) {
            ++S[col], ++pt;
            C[pt] = col, A[pt] = row, U[pt] = U[col], D[pt] = col;
            D[U[col]] = pt, U[col] = pt;
            if (~H[row]) {
                L[pt] = L[H[row]], R[pt] = H[row], L[R[pt]] = R[L[pt]] = pt;
            } else {
                H[row] = L[pt] = R[pt] = pt;
            }
    }

    inline void remove(int x) {
        L[R[x]] = L[x], R[L[x]] = R[x];
        for (int i = D[x]; i != x; i = D[i]) {
            for (int j = R[i]; j != i; j = R[j]) {
                U[D[j]] = U[j], D[U[j]] = D[j], --S[C[j]];
            }
        }
    }

    inline void resume(int x) {
        for (int i = U[x]; i != x; i = U[i]) {
            for (int j = L[i]; j != i; j = L[j]) {
                U[D[j]] = j, D[U[j]] = j, ++S[C[j]];
            }
        }
        L[R[x]] = x, R[L[x]] = x;
    }

    bool dlx(int k) {
        if (R[0] == 0) 
        {
            totAns = k;
            return true;
        }
        int col = R[0];
        for (int i = R[0]; i != 0; i = R[i]) {
            if (S[col] > S[i]) col = i;
        }
        if (S[col] == 0) return false;
        remove(col);
        for (int i = D[col]; i != col; i = D[i]) {
            ans[k] = A[i];
            for (int j = R[i]; j != i; j = R[j]) remove(C[j]);
            if (dlx(k + 1)) return true;
            for (int j = L[i]; j != i; j = L[j]) resume(C[j]);
        }
        resume(col);
        return false;
    }
    // call dlx(0)
}DLX;
