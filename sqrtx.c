int mySqrt(int x) {
    if (x <= 0)
        return (uint16_t)(x >> 31);
    // knowing (H+L)^2 = H^2 + 2HL + L^2
    // partitioned      H^^^  M^^^  L^^^
    // want r_n and r_0 = 0
    // let d_i = ..., 2^2, 2^1, 2^0 aka d_n = 1
    // r_i = r_{i-1} + d_i, d_i = 2^{n-i}
    // S_i = r_i^2
    //     = r_{i-1}^2 + 2d_{i}r_{i-1} + d_{i}^2
    //     = H_i + M_i + L_i
    // H_i = r_{i-1}^2
    // M_i = 2d_{i}r_{i-1} = 2^{n-i+1}r_{i-1}
    // L_i = d_{i}^2 = 2^{2(n-i)}
    // H_{i+1} = r_i^2 = S_i = H_i + M_i + L_i
    // L_{i+1} = 2^{2(n-(i+1))} = L_i*2^{-2}
    // M_{i+1} = 2^{n-i}r_i
    //         = 2^{n-i}r_{i-1}+2^{n-i}*2^{n-i}
    //         = (M_i+2L_i)*2^{-1}
    // having another
    // r_j = r_{j-1}
    // H_{j+1} = r_j^2 = r_{j-1}^2 = H_j
    // L_{j+1} = 2^{2(n-(j+1))} = L_j*2^{-2}
    // M_{j+1} = 2^{n-j}r_j
    //         = 2^{n-j}r_{j-1}
    //         = M_j*2^{-1}
    unsigned const shift = 15;
    unsigned d = 1U << shift, r, H, M, L;
    for (H = M = r = 0, L = d << shift; d != 0 && H < x; L >>= 2, M >>= 1, d >>= 1)
        if (H + M + L <= x)
            r += d, H += M + L, M += L << 1;
    return r;
}
