mkdir -p build/pico

for REPO in sdk examples playground extras
do
	DESTINATION="build/pico/pico-$REPO"

	if [ -d $DESTINATION ]; then
		echo "already have pico-$REPO"
	fi

	git clone --recursive "https://github.com/raspberrypi/pico-$REPO" "$DESTINATION"
done
