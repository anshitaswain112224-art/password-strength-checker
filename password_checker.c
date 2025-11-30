#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Function Prototypes
int containsUpper(const char *p);
int containsLower(const char *p);
int containsDigit(const char *p);
int containsSpecial(const char *p);
int lengthScore(int len);
double calculateEntropy(const char *p);
void giveSuggestions(int upper, int lower, int digit, int special, int length);

int main() {
    char password[200];
    int upper, lower, digit, special, length;
    int score = 0;
    double entropy;

    printf("=========================================\n");
    printf("         ADVANCED PASSWORD CHECKER        \n");
    printf("=========================================\n\n");

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);

    // Remove newline from fgets
    length = strlen(password);
    if (password[length - 1] == '\n') {
        password[length - 1] = '\0';
        length--;
    }

    // Function Calls
    upper = containsUpper(password);
    lower = containsLower(password);
    digit = containsDigit(password);
    special = containsSpecial(password);
    score += lengthScore(length);
    score += upper + lower + digit + special;

    entropy = calculateEntropy(password);

    // Output
    printf("\n======= PASSWORD ANALYSIS =======\n");
    printf("Password: %s\n", password);
    printf("Length              : %d\n", length);
    printf("Contains Uppercase  : %s\n", upper ? "Yes" : "No");
    printf("Contains Lowercase  : %s\n", lower ? "Yes" : "No");
    printf("Contains Digit      : %s\n", digit ? "Yes" : "No");
    printf("Contains Special    : %s\n", special ? "Yes" : "No");
    printf("Estimated Entropy   : %.2f bits\n", entropy);

    printf("\nStrength: ");

    if (score <= 2)
        printf("WEAK\n");
    else if (score <= 4)
        printf("MEDIUM\n");
    else if (score <= 6)
        printf("STRONG\n");
    else
        printf("VERY STRONG\n");

    giveSuggestions(upper, lower, digit, special, length);

    return 0;
}

/* ======= Function Definitions ======= */

int containsUpper(const char *p) {
    while (*p) {
        if (isupper(*p)) return 1;
        p++;
    }
    return 0;
}

int containsLower(const char *p) {
    while (*p) {
        if (islower(*p)) return 1;
        p++;
    }
    return 0;
}

int containsDigit(const char *p) {
    while (*p) {
        if (isdigit(*p)) return 1;
        p++;
    }
    return 0;
}

int containsSpecial(const char *p) {
    while (*p) {
        if (!isalnum(*p) && !isspace(*p))
            return 1;
        p++;
    }
    return 0;
}

int lengthScore(int len) {
    if (len >= 12) return 3;
    if (len >= 8) return 2;
    if (len >= 6) return 1;
    return 0;
}

double calculateEntropy(const char *p) {
    int charset = 0;

    if (containsUpper(p)) charset += 26;
    if (containsLower(p)) charset += 26;
    if (containsDigit(p)) charset += 10;
    if (containsSpecial(p)) charset += 32;

    return strlen(p) * log2(charset);
}

void giveSuggestions(int upper, int lower, int digit, int special, int length) {
    printf("\n======= SUGGESTIONS =======\n");

    if (length < 8)
        printf("- Use a longer password (at least 8–12 characters).\n");
    if (!upper)
        printf("- Add at least one UPPERCASE letter.\n");
    if (!lower)
        printf("- Add at least one lowercase letter.\n");
    if (!digit)
        printf("- Include digits (0–9).\n");
    if (!special)
        printf("- Use special characters (!, @, #, $, *, etc.).\n");

    if (upper && lower && digit && special && length >= 12)
        printf("- Great job! Your password is strong.\n");
}