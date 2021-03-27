/*
 * greg.c - Gregorian calendar logic
 */
static char *month_name[12] =
{
	"January",   "February", "March",    "April",
	"May",       "June",     "July",     "August",
	"September", "October",  "November", "December"
};

static char *mon_name[12] =
{
	"Jan", "Feb", "Mar", "Apr",
	"May", "Jun", "Jul", "Aug",
	"Sep", "Oct", "Nov", "Dec"
};

static char *day_name[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

static int days_in_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

char *get_month_name(int i)
{
    if(i < 0 || i > 11) return "ERR";
    return month_name[i];
}

char *get_mon_name(int i)
{
    if(i < 0 || i > 11) return "ERR";
    return mon_name[i];
}

char *get_day_name(int i)
{
    if(i < 0 || i > 6) return "ERR";
    return day_name[i];
}

int get_days_in_month(int i)
{
    if(i < 0 || i > 11) return 0;
    return days_in_month[i];
}

void determine_leap_year(int year)
{
	if((year % 4 == 0 && year % 100 != 0) || year % 400 ==0) days_in_month[1] = 29;
	else days_in_month[1] = 28;
}

int zeller(int month, int year)
{
	month++; // Normalize month for Zeller's algorithm
    int day = 1, z_month, z_year, offset;

    if(month < 3) z_month = month + 10;
    else z_month = month - 2;
    if(z_month > 10) z_year = year - 1;
    else z_year = year;
    offset = ((int)((13 * z_month - 1) / 5) + day + z_year % 100 +
             (int)((z_year % 100) / 4) - 2 * (int)(z_year / 100) +
             (int)(z_year / 400) + 77) % 7;

    return offset;
}