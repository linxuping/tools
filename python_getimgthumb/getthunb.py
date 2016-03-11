import Image

def get_img_thumb(url):
    im=Image.open(url)
    maxsize=160
    l,t,r,b=0,0,0,0
    w,h = im.size
    w_old,h_old=im.size
    if w<maxsize and h<maxsize:
        return url
    elif w > h:
        print im.size
        w = int(maxsize/float(h)*w)
        h = maxsize
        l,t=(w-maxsize)/2,0
        r,b=l+maxsize,t+maxsize if t+maxsize<h else h
        print l,t,r,b
    elif w < h:
        h = int(maxsize/float(w)*h)
        w = maxsize
        l,t=0,(h-maxsize)/2
        r,b=l+maxsize if l+maxsize<w else w,t+maxsize
    #ex process.
    if (w_old!=w or h_old!=h) and l+t+r+b>0:
        im_new = im.resize((w,h), Image.ANTIALIAS)
        box = (l,t,r,b)
        region = im_new.crop(box)
        tmps=url.rsplit(".",1)
        url = "%s_%d.png"%(tmps[0],maxsize)
        region.save(url)
    return url
get_img_thumb("h.png")
get_img_thumb("v.png")
get_img_thumb("h_long.png")
get_img_thumb("v_long.png")

