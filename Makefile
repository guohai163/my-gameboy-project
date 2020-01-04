CC	= /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

BINS	= main.gb

all:	$(BINS)



%.o:	%.c
	$(CC) -c -o $@ $<

%.gb:	main.o BoyAndGirl.o RewardCard.o Ground.o Background.o
	$(CC) -o $@ $^



clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm