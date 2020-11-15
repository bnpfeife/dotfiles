/** GEOLOCATION ***/
/* 0201: disable Location-Aware Browsing
 * [NOTE] Best left at default "true", fingerprintable, is already behind a prompt (see 0202)
 * [1] https://www.mozilla.org/firefox/geolocation/ ***/
   // user_pref("geo.enabled", false);
user_pref("geo.enabled", false);

user_pref("layers.acceleration.force-enabled", true);
