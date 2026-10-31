# bond-pricing-tool

A small C++ command-line tool for pricing fixed-coupon bonds and computing their
standard risk measures. It reads bonds from a CSV file, works out each bond's
cash flows, yield-to-maturity, discount factors and durations, and writes a
period-by-period cash-flow table to `out.txt`. It also includes early support for
pricing a bond off a yield curve, interpolating between the rates you supply.

Dollar amounts are held in a fixed-point `Money` type (6 decimal places stored
in a `long long`) so cash-flow sums don't pick up floating-point rounding drift.

> **Status:** work in progress. `main.cpp` currently runs a yield-curve
> interpolation demo; the CSV → `out.txt` pipeline is commented out while the
> interpolation and curve-based pricing code is being tested.

## Building

Requires a C++23 compiler (`g++` by default).

```bash
make all
```

This produces the `main` executable. `make clean` removes it and the object
files. Note that plain `make` runs `clean`, since it is the first rule in the
Makefile.

## Usage

```bash
./main bonds.csv
```

With the CSV pipeline enabled, this reads every bond in the file and writes the
results to `out.txt`.

### Input format

One bond per line, no header row:

```
face_value,current_price,coupon_rate,years_to_maturity,coupon_frequency
```

| Field               | Example  | Meaning                                         |
| ------------------- | -------- | ----------------------------------------------- |
| `face_value`        | `1000.00`| Par value paid back at maturity                 |
| `current_price`     | `1000.00`| Price the bond trades at today                  |
| `coupon_rate`       | `0.06`   | Annual coupon rate as a decimal (6%)            |
| `years_to_maturity` | `3`      | Whole years until the bond matures              |
| `coupon_frequency`  | `1`      | Coupon payments per year (1 annual, 2 semiannual, 4 quarterly) |

Write dollar amounts with a decimal point and two decimal places (`1000.00`),
since `Money` parses the dollars and cents separately. See `bonds.csv` for a
sample.

### Output

For each bond, `out.txt` contains a table of every coupon period:

```
Period | Cash Flow | Discount Factor | Present Value
----------------------------------------------------
```

followed by the Macaulay duration, modified duration, total future cash
received and its present value.

## Calculations done in this project

1. **Periodic Coupon Payment:** e.g. a $1000 bond at a 5% coupon rate with 1
   period a year pays $50 per payment.
2. **Newton-Raphson Method (NRM):** root-finding used to solve for the
   yield-to-maturity.
3. **Yield-to-Maturity (YTM):** estimates the bond's YTM by passing 0.05 as the
   starting guess to NRM.
4. **Discount Factor:** uses the bond info and YTM to discount the cash flow of
   a given period, `1 / (1 + ytm/freq)^periods`.
5. **Flat Curve Discount Rate:** uses the YTM and the other bond data to build a
   flat-curve rate.
6. **Macaulay Duration:** the weighted-average time (in years) until the bond's
   cash flows are received, weighted by each flow's present value.
7. **Modified Duration:** Macaulay duration divided by `1 + ytm/freq`; the
   approximate percentage price change for a 1% change in yield.
8. **Convexity:** the second-order sensitivity of price to yield, which
   corrects the duration estimate for larger rate moves.
9. **Rate Interpolation:** fills in missing yield-curve points and linearly
   interpolates annual rates down to each coupon period.
10. **Curve-Based Pricing:** discounts each cash flow at its own interpolated
    curve rate instead of a single YTM.

## Project layout

| File            | Purpose                                                       |
| --------------- | ------------------------------------------------------------- |
| `main.cpp`      | Entry point: reads the CSV, runs the calculations, writes output |
| `core_calc.h/.cpp` | `Bond` struct, CSV parsing, and all pricing/risk calculations |
| `Money.h/.cpp`  | Fixed-point money type used for cash amounts                  |
| `bonds.csv`     | Sample input                                                  |
| `Makefile`      | Build rules                                                   |
