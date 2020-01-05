CC	= /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

BINS	= OurWorld.gb

all:	$(BINS)



%.o:	%.c
	$(CC) -c -o $@ $<

%.gb:	OurWorld.o BoyAndGirl.o RewardCard.o Ground.o Background.o GameRole.o
	$(CC) -o $@ $^



clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm