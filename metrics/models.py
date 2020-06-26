from django.db import models


class Metrics(models.Model):
    dttm = models.DateTimeField(verbose_name="Дата события", auto_now=True)
    temperature = models.PositiveIntegerField(verbose_name="Температура", default=0)
    carbon_dioxide = models.PositiveIntegerField(verbose_name="Углекислый газ", default=0)

