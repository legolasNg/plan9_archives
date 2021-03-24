#include <u.h>
#include <libc.h>
#include <authsrv.h>
#include "authcmdlib.h"

static char *pbmsg = "AS protocol botch";

int
asrdresp(int fd, char *buf, int len)
{
	char error[AERRLEN];

	if(read(fd, buf, 1) != 1){
		werrstr(pbmsg);
		return -1;
	}

	switch(buf[0]){
	case AuthOK:
		if(readn(fd, buf, len) < 0){
			werrstr(pbmsg);
			return -1;
		}
		break;
	case AuthErr:
		if(readn(fd, error, AERRLEN) < 0){
			werrstr(pbmsg);
			return -1;
		}
		error[AERRLEN-1] = 0;
		werrstr(error);
		return -1;
	default:
		werrstr(pbmsg);
		return -1;
	}
	return 0;
}

void
main(int argc, char **argv)
{
	int n, fd;
	Ticketreq tr;
	Ticket t;
	Passwordreq pr;
	char tbuf[TICKETLEN];
	char key[DESKEYLEN];
	char buf[512];
	char *s;

	ARGBEGIN{
	}ARGEND

	s = getenv("service");
	if(s && strcmp(s, "cpu") == 0){
		fprint(2, "passwd must not be run on the cpu server\n");
		exits("boofhead");
	}

	if(argc > 0)
		s = argv[0];
	else
		s = nil;

	fd = authdial(nil, s);
	if(fd < 0)
		error("protocol botch: %r");

	/* send ticket request to AS */
	memset(&tr, 0, sizeof(tr));
	if(argc == 0)
		strcpy(tr.uid, getuser());
	else
		strcpy(tr.uid, argv[0]);
	tr.type = AuthPass;
	convTR2M(&tr, buf);
	if(write(fd, buf, TICKREQLEN) != TICKREQLEN)
		error("protocol botch: %r");
	if(asrdresp(fd, buf, TICKETLEN) < 0)
		error("%r");
	memmove(tbuf, buf, TICKETLEN);

	/*
	 *  get a password from the user and try to decrypt the
	 *  ticket.  If it doesn't work we've got a bad password,
	 *  give up.
	 */
	readln("Plan 9 Password: ", pr.old, sizeof pr.old, 1);
	passtokey(key, pr.old);
	convM2T(tbuf, &t, key);
	if(t.num != AuthTp || strcmp(t.cuid, tr.uid))
		error("bad password");

	/* loop trying new passwords */
	for(;;){
		pr.changesecret = 0;
		*pr.new = 0;
		readln("change Plan 9 Password? (y/n) ", buf, sizeof buf, 0);
		if(*buf == 'y' || *buf == 'Y'){
			readln("Password(8 to 31 characters): ", pr.new,
				sizeof pr.new, 1);
			readln("Confirm: ", buf, sizeof buf, 1);
			if(strcmp(pr.new, buf)){
				print("!mismatch\n");
				continue;
			}
		}
		readln("change Inferno/POP password? (y/n) ", buf, sizeof buf, 0);
		if(*buf == 'y' || *buf == 'Y'){
			pr.changesecret = 1;
			readln("make it the same as your plan 9 password? (y/n) ",
				buf, sizeof buf, 0);
			if(*buf == 'y' || *buf == 'Y'){
				if(*pr.new == 0)
					strcpy(pr.secret, pr.old);
				else
					strcpy(pr.secret, pr.new);
			} else {
				readln("Secret(0 to 256 characters): ", pr.secret,
					sizeof pr.secret, 1);
				readln("Confirm: ", buf, sizeof buf, 1);
				if(strcmp(pr.secret, buf)){
					print("!mismatch\n");
					continue;
				}
			}
		}
		pr.num = AuthPass;
		convPR2M(&pr, buf, t.key);
		if(write(fd, buf, PASSREQLEN) != PASSREQLEN)
			error("AS protocol botch: %r");
		if(asrdresp(fd, buf, 0) == 0)
			break;
		fprint(2, "refused: %r\n");
	}
	close(fd);

	if(*pr.new){
		/* if this is the hostowner's key, try to change the key in the kernel */
		n = readfile("/dev/hostowner", buf, sizeof(buf)-1);
		if(n > 0){
			buf[n] = 0;
			if(strcmp(buf, tr.uid) == 0){
				passtokey(key, pr.new);
				writefile("/dev/key", key, DESKEYLEN);
			}
		}
	}
	exits(0);
}
