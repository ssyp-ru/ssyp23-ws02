while(1) {
        ADC_CSR &= ~(1 << 7);
        ADC_CR1 |= 1;
        while (!(ADC_CSR & (1 << 7)));
        x = ADC_DRH;
        x <<= 2;
        x |= ADC_DRL;
        ADC_CSR &= ~3;
        ADC_CSR |= 4;

        ADC_CSR &= ~(1 << 7);
        ADC_CR1 |= 1;
        while (!(ADC_CSR & (1 << 7)));
        y = ADC_DRH;
        y <<= 2;
        y |= ADC_DRL;
        ADC_CSR &= ~4;
        ADC_CSR |= 3;
        ADC_CSR &= ~(1 << 7);

        enable_tim4();
        while (tms < x) {
            PB_ODR |= 1 << 5;
            for (int t = 0; t < y; t += 2);
            PB_ODR &= ~(1 << 5);
            for (int t = 0; t < 1024 - y; t += 2);
        }
        disable_tim4();
        sleep(x);
    }
