typedef struct {
	char dict[41];
	int maxDif;
	int autoCorrect;
} Config;

Config* getConfig( void );
